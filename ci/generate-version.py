import sys
import os

if __name__ == '__main__':
    version = "4.2.1"
    try:
        p = os.popen('git rev-list --tags --max-count=1')
        commit = p.read().strip()
        p.close()

        if commit:
            p = os.popen('git describe --tags ' + commit)
            tag = p.read().strip()
            p.close()
            if tag:
                v = tag[1:] if tag.startswith('v') else tag
                if v:
                    version = v
    except Exception as e:
        print("Error getting tag:", e)

    print("Version to write:", version)
    version_file = os.path.abspath(os.path.join(os.path.dirname(__file__), "../QtScrcpy/appversion"))
    with open(version_file, 'w', encoding='utf-8') as f:
        f.write(version + "\n")
    sys.exit(0)