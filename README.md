
# 🎧 CxUnplugged

Welcome to **CxUnplugged** — your very own *command-line music manager*, written completely in C!  
Think of it as a chill unplugged session — but for your terminal. 🎸  

It’s small, simple, and modular — built to help you practice **file handling**, **linked lists**, and **command parsing** in C while having fun managing songs, albums, and playlists.

---

## 🕹️ What You Can Do (So Far)

- `ls` → 🎵 Lists all songs from your `list_of_songs.txt` file  
- `ca` → 💿 Create a new album *(coming soon)*  
- `oa` → 📂 Open an album *(feature under construction)*  
- `ss` → 🔍 Search songs *(planned)*  
- `pp` → ▶️ Play playlist *(planned)*  
- `next`, `prev`, `stop` → Basic playback commands (placeholders)  
- `exit` → 👋 Exit the program with style

Example run:
```

C-Unplugged!
~> ls
List of songs
1.Shape of You : Ed Sheeran
2.Blinding Lights : The Weeknd
3.Heat Waves : Glass Animals
4.Photograph : Ed Sheeran
~> exit
Thank you for your visit :)

```

---

## 🧩 Project Layout

```

CxUnplugged/
├── interface.c          # Main user interface (command parser)
├── songs.c / songs.h    # Song structure & file operations
├── albums.c / albums.h  # Album creation logic
├── playlists.c / playlists.h  # Playlist creation logic
├── list_of_songs.txt    # Your song library 🎶
└── Makefile             # Because typing gcc 4 times is boring

````

---

## 🧱 Build It (with Makefile)

If you’re using Linux or macOS, it’s super easy:
```bash
make
````

That’s it!
This will compile everything into an executable called **`cunplugged`**.

Run it with:

```bash
./cunplugged
```

If you ever want to clean things up:

```bash
make clean
```

---

## 🧠 Under the Hood

CxUnplugged uses:

* **Linked lists** for songs, albums, and playlists
* **File I/O** for storing song info
* **String parsing** (`strtok`, `strcmp`, etc.) for command input
* **Dynamic memory allocation** with `malloc`

Basically — a mix of C fundamentals + creativity 💡

---

## 🧭 Roadmap (Next Jams)

* 🎶 Add “create song” and “add to album” commands
* 🔎 Implement searching by artist/title
* 🧾 Save and load full playlists dynamically
* 🧼 Add error handling and memory cleanup
* 🕺 Maybe even some ASCII art for the UI (because why not)

---

## 👨‍💻 Creator

**Chirayu D. P.**

> "Code, compile, and vibe."
> GitHub → [@chirayudp](https://github.com/chirayudp)

---
