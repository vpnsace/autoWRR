FROM mcr.microsoft.com/playwright/python:v1.60.0-jammy

WORKDIR /app

COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

RUN python -m playwright install chromium

COPY . .

EXPOSE 8080

CMD ["gunicorn", "--timeout", "300", "--bind", "0.0.0.0:8080", "app:app"]