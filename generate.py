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
# GENERATE PDF (2 PAGES)
# =========================

    print("📄 Creating PDF...")
    
    
    PAGE_WIDTH = 612
    PAGE_HEIGHT = 792

    # ----------------------------------
    # PAGE 1 : CODE
    # ----------------------------------

    code_img = Image.open(code_png)
    code_w, code_h = code_img.size

    max_width = PAGE_WIDTH - 40
    max_height = 650

    ratio = min(
        max_width / code_w,
        max_height / code_h
    )

    new_w = code_w * ratio
    new_h = code_h * ratio

    x = (PAGE_WIDTH - new_w) / 2
    y = 50

    pdf.drawImage(
        code_png,
        x,
        y,
        width=new_w,
        height=new_h
    )

    pdf.showPage()

    # ----------------------------------
    # PAGE 2 : OUTPUT
    # ----------------------------------

    output_img = Image.open(output_png)
    if str(theme) == "2":
        output_img = ImageOps.invert(
        output_img.convert("RGB")
    )
        
    temp_output = output_png

    if str(theme) == "2":

        temp_output = os.path.join(
            OUTPUT_DIR,
            f"{program_name}_invert.png"
        )

        output_img.save(temp_output)

    out_w, out_h = output_img.size

    ratio = min(
        max_width / out_w,
        max_height / out_h
    )

    new_w = out_w * ratio
    new_h = out_h * ratio

    x = (PAGE_WIDTH - new_w) / 2
    y = (PAGE_HEIGHT - new_h) / 2 - 30

    pdf.drawImage(
        temp_output,
        x,
        y,
        width=new_w,
        height=new_h
    )

    pdf.showPage()
    pdf.save()

    code_img.close()
    output_img.close()

    if str(theme) == "2" and os.path.exists(temp_output):
        os.remove(temp_output)

    print(f"✅ PDF Saved: {pdf_file}")


# =========================
# MERGE LAB MANUAL
# =========================

def merge_lab_manual(programmer_name):

    manual_pdf = os.path.join(
        PDF_DIR,
        "ADA_Lab_Manual Unit 1.pdf"
    )

    output_pdf = os.path.join(
        PDF_DIR,
        f"ADA_Report_{programmer_name}.pdf"
    )

    PROGRAM_PAGES = [
    ("1_linear_code.pdf", 1, 11),
    ("2_linear_code.pdf", 12, 14),
    ("3_binary_code.pdf", 15, 18),
    ("4_binary_code.pdf", 19, 22),
    ("5_heap_code.pdf", 23, 28),
    ("6_merge_code.pdf", 29, 31),
    ("7_quick_code.pdf", 32, 35),
    ("8_op_code.pdf", 36, 39),
    ("9_op_code.pdf", 40, 42),
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
    

