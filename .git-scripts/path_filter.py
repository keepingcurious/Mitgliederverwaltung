#!/usr/bin/env python3
import sys
import os
import argparse

# Definiere hier deine persönlichen Pfade und die Platzhalter, durch die sie ersetzt werden sollen
PATH_MAPPINGS = [
    # (Echter lokaler Pfad, Platzhalter im Git-Repository)
    (os.path.expanduser("~"), "__USER_HOME__"),
    # Falls du spezifische Projektpfade hast, kannst du sie hier hinzufügen:
    # ("/Users/deinname/Fotos/Source", "__SOURCE_DIR__"),
]

def clean(text):
    """Ersetzt lokale Pfade durch Platzhalter (vor dem Commit)."""
    for real_path, placeholder in PATH_MAPPINGS:
        if real_path:
            text = text.replace(real_path, placeholder)
    return text

def smudge(text):
    """Ersetzt Platzhalter durch lokale Pfade (beim Checkout/Clone)."""
    for real_path, placeholder in PATH_MAPPINGS:
        if real_path:
            text = text.replace(placeholder, real_path)
    return text

def main():
    parser = argparse.ArgumentParser(description="Git Clean/Smudge Filter for paths")
    parser.add_argument("--clean", action="store_true", help="Replace real paths with placeholders")
    parser.add_argument("--smudge", action="store_true", help="Replace placeholders with real paths")
    args = parser.parse_args()

    # Liest den Code von Git über stdin
    content = sys.stdin.read()

    if args.clean:
        content = clean(content)
    elif args.smudge:
        content = smudge(content)

    # Gibt den veränderten Code an Git über stdout zurück
    sys.stdout.write(content)

if __name__ == "__main__":
    main()
