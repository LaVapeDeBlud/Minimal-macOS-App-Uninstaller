# The Simplest App Uninstaller

**Tired of macOS app uninstallers that leave things behind?**
This is the simplest app uninstaller helper—only **93 lines of C++ code**—designed to **find all leftover files** in your `~/Library` so you can remove them manually.

It’s small, fast, and safe—**nothing is deleted automatically**.

---

## Features

* Searches common macOS app storage folders:

  * `~/Library/Application Support`
  * `~/Library/Preferences`
  * `~/Library/Caches`
  * `~/Library/Containers`
* Case-insensitive search for app names.
* Displays **all app-related files/folders** for manual cleanup.
* Automatically deletes app-related files/folders (Added in release 1.1.0).

---

## Example

```text
Enter the name of the app you want to uninstall: Slack
App paths in ~/Library are:
/Users/username/Library/Application Support/Slack
/Users/username/Library/Caches/com.tinyspeck.slackmacgap
/Users/username/Library/Preferences/com.tinyspeck.slackmacgap.plist
...
For safety, this app will not automatically delete anything. Please delete these files manually.
Press ENTER to exit
```

---
## Usage

* Download the compiled file from the releases section.
* Open the terminal.
* Go to wherever the file is stored.
Run ```text
./macOS_App_Cleaner
```
or whatever the file is named on your system.

---
## Notes

* Only searches **user-level library folders**; no `sudo` required.
* Skips `Containers` folder to avoid macOS permission prompts.
* Safe: does **not delete anything automatically**.

---

## License

* This project is licensed under the GNU General Public License v3.0.
* See the LICENSE file for details.
---
