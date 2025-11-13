# Kalkulator Eliminasi Gauss (3×4)

Proyek ini berisi aplikasi web interaktif untuk menghitung eliminasi Gauss pada matriks 3×4 menggunakan C++ CGI.

## Struktur Folder
```
gauss-matrix-calculator/
├── index.html
├── cgi-bin/
│   └── gauss.cpp
│   └── gauss.cgi
```

## Cara Menjalankan
1. Kompilasi program C++:
```bash
cd cgi-bin
g++ -O2 -std=c++17 gauss.cpp -o gauss.cgi
chmod +x gauss.cgi
```
2. Jalankan server lokal:
```bash
cd ..
python3 -m http.server --cgi 8000
```
3. Buka di browser:
```
http://localhost:8000/index.html
```
