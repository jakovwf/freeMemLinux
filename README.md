# freeMemLinux

Ovaj program prikazuje **tačnu količinu slobodne memorije** na Linux-u u gigabajtima (GB).

---

## ⚡ Funkcionalnost

- Proverava ukupnu slobodnu memoriju
- Ispisuje rezultat u GB
- Ne koristi spoljne biblioteke osim standardnog C-a
- Radi direktno iz terminala

---

## 🛠️ Instalacija i kompajliranje

### 1️⃣ Kompajliranje programa

U terminalu pokreni:

```bash
gcc main.c -o ime_programa
```

Zameni `ime_programa` željenim imenom izvršnog fajla.

---

### 2️⃣ (Opcionalno) Instalacija kao globalna komanda

Da bi mogao da pokrećeš program sa bilo kog mesta, prebacite ga u `/usr/local/bin`:

```bash
sudo mv ime_programa /usr/local/bin/
```

---

## ▶️ Korišćenje

Jednostavno pokreni program u terminalu:

```bash
./ime_programa
```

Ako je instaliran u `/usr/local/bin`, možeš ga pozvati direktno po imenu:

```bash
ime_programa
```

Program će ispisati:

```
Ukupno slobodno: XX.XX GB
```

---

## 🔍 Kako radi

1. Program koristi **pipe** i **fork** za pokretanje `df -B1` komande.
2. Parsira izlaz da bi izvukao slobodnu memoriju (`avail`) za sve fajl sisteme.
3. Sabira sve vrednosti i prikazuje rezultat u gigabajtima.
4. Ignoriše zaglavlje `df` komande.

---

## ⚙️ Zahtevi

- Linux operativni sistem
- `gcc` kompajler
- Sudo privilegije ako želiš globalnu instalaciju

---

## 👤 Autor

Jakov Jovanović  
