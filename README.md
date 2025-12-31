# The Simplest App Uninstaller

**Tired of macOS app uninstallers that leave things behind?**
This is the simplest app uninstaller helper—only **33 lines of C++ code**—designed to **find all leftover files** in your `~/Library` so you can remove them manually.

It’s small, fast, and safe—**nothing is deleted automatically**.

---

## Features

* Searches common macOS app storage folders:

  * `~/Library/Application Support`
  * `~/Library/Preferences`
  * `~/Library/Caches`
  * `~/Library/Containers`
* Case-insensitive search for app names.
* Only **33 lines of code**—easy to read and modify.
* Displays **all app-related files/folders** for manual cleanup.


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

## Notes

* Only searches **user-level library folders**; no `sudo` required.
* Optional: skip `Containers` folder to avoid macOS permission prompts.
* Safe: does **not delete anything automatically**.

---

## License

This project is licensed under the GNU General Public License v3.0.
See the LICENSE file for details.
---
