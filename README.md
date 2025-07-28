# Contact Manager in C using Static Memory Pool Allocation

This is a simple **Contact Manager** project written in **C**, designed to run in **memory-constrained environments** such as embedded systems.  
Instead of using dynamic memory (`malloc`/`free`), it uses **static memory pool allocation**, which is efficient and deterministic — a key requirement in real-time systems.

---

## Features

- Add new contacts
- Edit existing contacts
- Delete contacts by index
- Compact the memory pool (remove fragmentation)
- View memory pool usage (used/free blocks)
- Input validation:
  - Phone number (must be 10 digits)
  - Email (must contain `@` and `.`)

---

## Key Concepts Used

- **Static memory management** (fixed-size memory pool)
- **Struct-based contact records**
- **Manual memory compaction**
- **Pointer arithmetic and memory offsets**
- **No dynamic memory allocation**

---
## Sample Output
**------Contact Manager------**
1. Add New Contact
2. View All Contacts
3. Delete Contact (by index)
4. Edit Contact (by index)
5. Compact Memory Pool(to avoid Fragmentation)
6. Pool Status
7. Exit
Choose option: 1
Enter Contact ID: 101
Enter Name: Priya Sharma
Enter Phone (10 digits): 9876543210
Enter Email: priya@example.com
Contact added at index 0
---
## Tools Used
**Language:** C
**Compiler:** GCC 
**Platform:** Windows Terminal
**Editor:** Code::Blocks 

## What I Learned 
- Managing memory manually using fixed-size pools
- Writing modular and reusable C code
- Using pointers, structs, and memory offsets in a real-world way

## 👩‍💻 Author

**Priyanka G**  
https://www.linkedin.com/in/priyanka-g-932b33232/
Feel free to connect or reach out for collaboration or feedback!

## 📝 License

This project is licensed under the **MIT License** – feel free to use or modify it with credit.
