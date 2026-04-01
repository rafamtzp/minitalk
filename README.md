
# minitalk

*This project has been created as part of the 42 curriculum by ramarti2.*

---

## 📖 Description

**minitalk** is a communication project from the 42 curriculum that explores inter-process communication using UNIX signals.

The goal of the project is to implement a **client-server system** where messages are transmitted from a client process to a server process using only two signals:

* `SIGUSR1`
* `SIGUSR2`

Each character is encoded in binary and sent bit by bit using signals. The server reconstructs the message and displays it once fully received.

This project helps develop a deeper understanding of:

* UNIX signals
* Process communication
* Bitwise operations and working with binary numbers in general
* Signal handling and synchronization

Note: I personally didn't use bitwise operations because at the time, they didn't seem necessary.  Instead I encoded/decoded characters into binary by subtracting/adding powers of 2, though I could've easily used bitwise operators had I known more about them.

---

## ⚙️ Instructions

### 🛠️ Compilation

To compile the project:

```bash
make
```

This will generate two executables:

```bash
./server
./client
```

---

### ▶️ Usage

#### 1. Start the Server

```bash
./server
```

The server will display its **PID** (Process ID). You will need this to send messages.

---

#### 2. Run the Client

```bash
./client <server_pid> "Your message here"
```

Example:

```bash
./client 12345 "Hello, world!"
```

---

### 🔄 How It Works

* The client converts each character into binary.
* Each bit is sent as a signal:

  * `SIGUSR1` → represents binary `1`
  * `SIGUSR2` → represents binary `0`
* The server receives signals and reconstructs characters bit by bit.
* Once a full message is received, it is printed to the standard output.

---

## 🧠 Concepts Learned

This project covers key low-level programming and system concepts:

* **UNIX signals (`SIGUSR1`, `SIGUSR2`)**
* **Signal handling with `sigaction`**
* **Binary encoding and decoding**
* **Process IDs (PID)**
* **Client-server architecture**

---

## 🛠️ Features

* Reliable message transmission using signals
* Binary encoding/decoding of characters
* Robust error handling (invalid PID, empty messages, etc.)
* Clean and modular code structure

### ✅ Bonus features

* Acknowledgment system (server confirms receipt of each bit or character)
* Support for Unicode characters
* Improved transmission speed and reliability

---

## 📚 Resources

### UNIX & Signals

* `man signal`
* `man sigaction`
* UNIX process communication documentation

---

## 🚀 Example

Terminal 1:

```bash
./server
```

Output:

```
PID: 12345
```

Terminal 2:

```bash
./client 12345 "Hello, server!"
```

Server output:

```
client: Hello, server!
```

---

## ⚠️ Error Handling

The program should handle:

* Invalid or missing PID
* Empty messages
* Signal transmission errors

---

## 🧾 Final Notes

minitalk is an excellent introduction to low-level communication between processes. It reinforces how data can be transmitted using minimal system primitives and builds a strong foundation for understanding operating systems.  It also challenged me to optimize it and make it more reliable using a the feedback system (with sigaction) that the bonus asks for.
