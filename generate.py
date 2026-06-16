import os
import re
from playwright.sync_api import sync_playwright
from reportlab.lib.pagesizes import letter
from reportlab.pdfgen import canvas
from PIL import Image,ImageOps
from pypdf import PdfReader, PdfWriter

# =========================
# DIRECTORIES
# =========================


BASE_DIR = os.path.dirname(os.path.abspath(__file__))

TEMPLATES_DIR = os.path.join(BASE_DIR, "templates")
PAGES_DIR = os.path.join(BASE_DIR, "Pages")
OUTPUT_DIR = os.path.join(BASE_DIR, "output")
PDF_DIR = os.path.join(BASE_DIR, "pdf")

os.makedirs(PDF_DIR, exist_ok=True)

# =========================
# SYNTAX HIGHLIGHTER
# =========================

def cpp_syntax_highlighter(text):

    text = (
        text.replace("&", "&amp;")
        .replace("<", "&lt;")
        .replace(">", "&gt;")
    )

    text = re.sub(
        r'(\/\*[\s\S]*?\*\/|\/\/.*)',
        r'<span class="comment">\1</span>',
        text
    )

    text = re.sub(
        r'(#\w+)',
        r'<span class="directive">\1</span>',
        text
    )

    text = re.sub(
        r'\b(cin|cout)\b',
        r'<span class="io">\1</span>',
        text
    )

    text = re.sub(
        r'\b(std)\b',
        r'<span class="type">\1</span>',
        text
    )

    text = re.sub(
        r'\b(main)(?=\s*\()',
        r'<span class="function">\1</span>',
        text
    )

    text = re.sub(
        r'\b(int|void|char|double|float|using|namespace|for|if|else|return|while|switch|case|break)\b',
        r'<span class="keyword">\1</span>',
        text
    )

    text = re.sub(
        r'\b(\d+)\b',
        r'<span class="literal">\1</span>',
        text
    )

    return text

# =========================
# MAIN
# =========================

def generate_lab_pdf(program_name, programmer_name,theme):

    print(f"\n🚀 Generating PDF for {program_name}")

    cpp_file = os.path.join(
        TEMPLATES_DIR,
        f"{program_name}.cpp"
    )

    code_template = os.path.join(
        PAGES_DIR,
         f"{theme}.html"
    )

    code_png = os.path.join(
        OUTPUT_DIR,
        f"{program_name}_code.png"
    )

    if str(theme) == "3":

        output_png = os.path.join(
            BASE_DIR,
            "output2",
            f"{program_name}.png"
        )

    else:

        output_png = os.path.join(
            OUTPUT_DIR,
            f"{program_name}.png"
        )

    pdf_file = os.path.join(
    PDF_DIR,
    f"{program_name}_code.pdf"
    )

    pdf = canvas.Canvas(
        pdf_file,
        pagesize=letter
    )

    

    # =========================
    # VALIDATION
    # =========================

    if not os.path.exists(cpp_file):
        print("❌ C++ file not found")
        return

    if not os.path.exists(code_template):
        print("❌ Pages/code.html not found")
        return

    if not os.path.exists(output_png):
        print(f"❌ Missing output image: {output_png}")
        return

    # =========================
    # READ CPP FILE
    # =========================

    with open(cpp_file, "r", encoding="utf-8") as f:
        cpp_code = f.read()
        cpp_code = cpp_code.replace("{NAME}", programmer_name)

    highlighted_code = cpp_syntax_highlighter(
        cpp_code
    )

    total_lines = len(
        cpp_code.splitlines()
    )

    line_numbers = "".join(
        f"<div>{i}</div>"
        for i in range(1, total_lines + 1)
    )

    # =========================
    # LOAD TEMPLATE
    # =========================

    with open(code_template, "r", encoding="utf-8") as f:
        code_html = f.read()

    code_html = code_html.replace(
        '<div class="line-numbers"></div>',
        f'<div class="line-numbers">{line_numbers}</div>'
    )

    code_html = code_html.replace(
        '<pre><code></code></pre>',
        f'<pre><code>{highlighted_code}</code></pre>'
    )

    # =========================
    # GENERATE CODE SCREENSHOT
    # =========================

    print("📸 Generating code screenshot...")

    try:

        with sync_playwright() as p:

            browser = p.chromium.launch(
                headless=True
            )

            page = browser.new_page(
                viewport={
                "width": 2500,
                "height": 1200
                },
                device_scale_factor=2
            )

            page.set_content(code_html)

            page.wait_for_selector(
                ".editor-container",
                timeout=10000
            )

            page.locator(
                ".editor-container"
            ).screenshot(
                path=code_png
            )

            browser.close()

    except Exception as e:
        print("❌ Playwright Error")
        print(e)
        return

    # =========================
    # GENERATE PDF (1 PAGE: CODE ON TOP, OUTPUT ON BOTTOM)
    # =========================

    print("📄 Creating PDF...")

    PAGE_WIDTH = 612
    PAGE_HEIGHT = 792

    MARGIN_X = 20
    MARGIN_TOP = 30
    MARGIN_BOTTOM = 30
    GAP = 20

    max_width = PAGE_WIDTH - (MARGIN_X * 2)
    available_height = PAGE_HEIGHT - MARGIN_TOP - MARGIN_BOTTOM - GAP
    code_section_height = available_height * 0.80    # 70% for code
    output_section_height = available_height * 0.20  # 30% for output

    def draw_fitted(image_path, box_x, box_y, box_w, box_h):

        img = Image.open(image_path)
        img_w, img_h = img.size

        ratio = min(
            box_w / img_w,
            box_h / img_h
        )

        new_w = img_w * ratio
        new_h = img_h * ratio

        x = box_x + (box_w - new_w) / 2
        y = box_y + (box_h - new_h) / 2

        pdf.drawImage(
            image_path,
            x,
            y,
            width=new_w,
            height=new_h
        )

        img.close()

    # ----------------------------------
    # OUTPUT — prepare inverted copy if needed (theme 2)
    # ----------------------------------

    temp_output = output_png

    if str(theme) == "2":

        output_img = Image.open(output_png)
        output_img = ImageOps.invert(
            output_img.convert("RGB")
        )

        temp_output = os.path.join(
            OUTPUT_DIR,
            f"{program_name}_invert.png"
        )

        output_img.save(temp_output)
        output_img.close()

    # ----------------------------------
    # CODE — top half of the page
    # ----------------------------------

    code_box_x = MARGIN_X
    code_box_y = MARGIN_BOTTOM + GAP + output_section_height
    code_box_w = max_width
    code_box_h = code_section_height

    draw_fitted(
        code_png,
        code_box_x,
        code_box_y,
        code_box_w,
        code_box_h
    )

    # ----------------------------------
    # OUTPUT — bottom half of the page
    # ----------------------------------

    output_box_x = MARGIN_X
    output_box_y = MARGIN_BOTTOM
    output_box_w = max_width
    output_box_h = output_section_height

    draw_fitted(
        temp_output,
        output_box_x,
        output_box_y,
        output_box_w,
        output_box_h
    )

    pdf.showPage()
    pdf.save()

    if str(theme) == "2" and os.path.exists(temp_output):
        os.remove(temp_output)

    print(f"✅ PDF Saved: {pdf_file}")


# =========================
# MERGE LAB MANUAL
# =========================

def merge_lab_manual(programmer_name):

    manual_pdf = os.path.join(
        PDF_DIR,
        "Unit_2_manual.pdf"
    )

    output_pdf = os.path.join(
        PDF_DIR,
        f"ADA_Report_{programmer_name}.pdf"
    )

    PROGRAM_PAGES = [
    ("1_code.pdf", 1, 6),
    ("2_code.pdf", 7, 10),
    ("3_code.pdf", 11, 13),
    ("4_code.pdf", 14, 17),
    ("5_code.pdf", 18,21),
    ("6_code.pdf", 22, 25),
    ("7_code.pdf", 26, 28),
    ("8_code.pdf", 29, 32),
    ]

    writer = PdfWriter()

    manual = PdfReader(manual_pdf)

    for pdf_name, start_page, end_page in PROGRAM_PAGES:

        for page_no in range(start_page - 1, end_page):
            writer.add_page(
                manual.pages[page_no]
            )

        generated_pdf = os.path.join(
            PDF_DIR,
            pdf_name
        )

        if os.path.exists(generated_pdf):

            code_pdf = PdfReader(
                generated_pdf
            )

            for page in code_pdf.pages:
                writer.add_page(page)

        else:

            print(
                f"⚠ Missing: {pdf_name}"
            )

    with open(output_pdf, "wb") as f:
        writer.write(f)

    print(
        f"✅ Final Report Saved: {output_pdf}"
    )

# ========================= 
# CLEANUP
# =========================
def cleanup_generated_files():

    print("\n🧹 Cleaning temporary files...")

    # Delete generated PDFs
    for file in os.listdir(PDF_DIR):

        if file.endswith("_code.pdf"):

            try:
                os.remove(
                    os.path.join(PDF_DIR, file)
                )
                print(f"🗑 Deleted {file}")

            except Exception as e:
                print(f"❌ Failed: {file}")

    # Delete output images
    for file in os.listdir(OUTPUT_DIR):

        if file.endswith("_code.png"):

            try:
                os.remove(
                    os.path.join(OUTPUT_DIR, file)
                )
                print(f"🗑 Deleted {file}")

            except Exception as e:
                print(f"❌ Failed: {file}")

    print("✅ Cleanup Complete")

# ========================= 
# BUILD MANUAL
# =========================
def build_manual(programmer_name, theme):

    theme = int(theme)

    if theme < 1 or theme > 3:
        theme = 1

    cpp_files = sorted([
        f for f in os.listdir(TEMPLATES_DIR)
        if f.endswith(".cpp")
    ])

    if not cpp_files:
        raise Exception("No .cpp files found")

    for cpp_file in cpp_files:

        program_name = os.path.splitext(
            cpp_file
        )[0]

        generate_lab_pdf(
            program_name=program_name,
            programmer_name=programmer_name,
            theme=theme
        )

    merge_lab_manual(programmer_name)
    cleanup_generated_files()

    return os.path.join(
        PDF_DIR,
        f"ADA_Report_{programmer_name}.pdf"
    )

# =========================
# ENTRY
# =========================

if __name__ == "__main__":

    programmer_name = input(
        "Enter Programmer Name: "
    )

    theme = input(
        "PRESS 1 FOR VS CODE DARK THEME\n"
        "PRESS 2 FOR VS CODE LIGHT THEME\n"
        "PRESS 3 FOR DEV C++ LIGHT THEME\n"
        "Enter the theme number: "
    )

    theme = int(theme)
    if theme < 1 or theme > 3:
        print("Invalid theme. Using Theme 1")
        theme = 1

    cpp_files = sorted([
        f for f in os.listdir(TEMPLATES_DIR)
        if f.endswith(".cpp")
    ])

    if not cpp_files:
        print("❌ No .cpp files found")
        exit()

    for cpp_file in cpp_files:

        program_name = os.path.splitext(
            cpp_file
        )[0]

        generate_lab_pdf(
            program_name=program_name,
            programmer_name=programmer_name,
            theme=theme
        )
    print("\n🎉 All Program PDFs Generated")
    merge_lab_manual(
    programmer_name
    )
    cleanup_generated_files()