Here is a **clean, simple, non-flashy, clear README** for your C-Unplugged music manager project.

---

# **C-Unplugged – README**

C-Unplugged is a **terminal-based music manager** written in C.
It lets you:

* Load a music library from a file
* Play songs (with next/prev queue navigation)
* Create albums and playlists
* Add or remove songs inside albums/playlists
* Search through songs
* Maintain a command log

Everything is stored in simple `.txt` files.

---

# **📁 Project Structure**

```
cunplugged/
│
├── interface.c
├── songs.c
├── songs.h
├── albums.c
├── albums.h
├── playlists.c
├── playlists.h
├── log.c
├── log.h
│
├── library.txt
├── albums.txt
├── playlists.txt
│
├── albums/
│     └── a<ID>.txt        (album song IDs)
├── playlists/
│     └── p<ID>.txt        (playlist song IDs)
│
└── Makefile
```

---

# **🔧 Building the Program**

Make sure you have GCC installed.

Compile using:

```
make
```

This creates an executable:

```
./cunplugged
```

To clean object files:

```
make clean
```

---

# **▶️ Running the Program**

Run:

```
./cunplugged
```

You will see the main menu:

```
1. List Songs
2. Search Song
3. List Albums
4. Create Album
5. Open Album
6. Create Playlist
7. Open Playlist
8. Show Command Log
9. Exit
```

---

# **📚 How to Use Each Feature**

## **1. List Songs**

Shows the full library loaded from `library.txt`.

---

## **2. Search Song**

Syntax:

```
<title/artist/genre> <keyword>
```

Example:

```
title Love
artist Arijit
genre Pop
```

After results, you can choose a song number to play.
This builds a **temporary play queue** and sets the global `currsong`.

---

## **3. List Albums**

Shows albums stored in `albums.txt`.

---

## **4. Create Album**

Prompts for an album name, adds it to `albums.txt` and creates:

```
albums/a<ID>.txt
```

---

## **5. Open Album**

Allows:

* List songs inside album
* Add a song from the library
* Delete a song
* Search inside album
* Play a song from album → automatically builds queue

---

## **6. Create Playlist**

Adds a new playlist to `playlists.txt` and creates:

```
playlists/p<ID>.txt
```

---

## **7. Open Playlist**

Allows:

* List playlist songs
* Add song
* Delete song
* Play next
* Play previous
* Looping next/prev navigation

NOTE: Songs in playlists are stored by ID in their respective file.

---

## **8. Show Command Log**

Displays actions written using:

```
logcmd("message");
```

Log file is:

```
cmdlog.txt
```

---

# **🎵 Playing Music (Important)**

Whenever you *play* a song (from search, album, or playlist):

* A **new queue** is created from the list
* `currsong` is set to the selected track
* `playnext()` moves forward
* `playprev()` moves backward
* Global queue pointer (`playqueue`) is updated

---

# **📄 Files Used**

### **library.txt**

Full master list of all songs.
Format:

```
<ID>
<Title>
<Artist>
<Genre>
<Duration>
(blank line)
```

### **albums.txt**

Stores all albums with:

```
<album_count>
<ID>
<album name>

<ID>
<album name>

...
```

### **albums/a<ID>.txt**

Stores song IDs inside an album.

---

### **playlists.txt**

Same layout as albums.

### **playlists/p<ID>.txt**

Stores song IDs inside each playlist.

---

### **cmdlog.txt**

Appends every playback action.

---

# **✔️ Requirements**

* GCC compiler
* Standard C libraries
* `albums/` and `playlists/` folders must exist

---

# **📝 Notes**

* Program uses **doubly linked lists** for playback navigation.
* Adding or deleting songs modifies only the in-memory linked list; saving writes back.
* Queue is always rebuilt whenever playing a song from library, album, or playlist.
* No audio is played — this is a *simulated* music player.

---

If you want, I can also generate:

✅ A version with Markdown formatting for GitHub
✅ A compact README for assignment submission
✅ A version with images / diagrams
Just tell me.
