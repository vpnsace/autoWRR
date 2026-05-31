from flask import Flask, render_template, request, send_file
import generate

app = Flask(
    __name__,
    template_folder="web"
)

@app.route("/")
def home():
    return render_template("index.html")


@app.route("/generate", methods=["POST"])
def generate_pdf():

    programmer_name = request.form.get("programmer_name")
    theme = request.form.get("theme")

    pdf_file = generate.build_manual(
        programmer_name,
        theme
    )

    return send_file(
        pdf_file,
        as_attachment=True
    )


if __name__ == "__main__":
    app.run(debug=True)