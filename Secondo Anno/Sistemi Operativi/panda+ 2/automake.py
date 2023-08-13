import os
import subprocess
import time
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

# Specify the folders to watch and the folder where the Makefile is located
watched_folder = '.'
makefile_folder = '.'

class FileChangeHandler(FileSystemEventHandler):
    def on_any_event(self, event):
        if event.is_directory:
            return
        #print(f"File change detected: {event.src_path}")
        # Run the "make" command in the specified folder
        try:

            # Stop if already run make in the last 5 seconds by saving a tmp file
            if os.path.exists('tmp'):
                if time.time() - os.path.getmtime('tmp') < 5:
                    return
            with open('tmp', 'w') as f:
                f.write('tmp')


            os.chdir(makefile_folder)
            subprocess.run('make && make clean', shell=True)
        except Exception as e:
            print(f"Error running 'make': {e}")

if __name__ == "__main__":
    event_handler = FileChangeHandler()
    observer = Observer()
    observer.schedule(event_handler, watched_folder, recursive=True)
    observer.start()

    print(f"Watching folder: {watched_folder}")
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        observer.stop()
    observer.join()
