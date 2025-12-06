#!/usr/bin/env bash
set -euo pipefail
echo "Hello World"
### CONFIG ###################################################################

# Binary name of your compiled simulation
PROJECT_BINARY="manager"

# How to build it (edit this if you don't use make)
BUILD_CMD="make"   # e.g. "g++ -std=c++17 -O2 -o manager src/*.cpp"

# Apt packages that correspond to your dependencies
APT_PACKAGES=(
  cmatrix          # Matrix rain
  sl               # Steam locomotive
  hollywood        # Multi-pane Hollywood hacker nonsense
  nsnake           # Snake clone
  chocolate-doom   # Doom
  ninvaders        # Space Invaders clone
  pacman4console   # Pac-Man clone
  greed            # Greed game
  2048             # 2048 puzzle
  nudoku           # Sudoku
  bsdgames         # includes hangman and other classics
)

### HELPERS ##################################################################

have_cmd() {
  command -v "$1" >/dev/null 2>&1
}

require_apt() {
  if ! have_cmd apt-get; then
    echo "ERROR: This setup script currently only supports Debian/Ubuntu (needs apt-get)."
    echo "On other distros, please install the dependencies manually:"
    echo "  ${APT_PACKAGES[*]}  +  asciiquarium  + deepseek-r1:1.5b (optional)"
    exit 1
  fi
}

apt_install_base_packages() {
  echo "Updating package list..."
  sudo apt-get update -y

  echo "Installing base packages..."
  sudo apt-get install -y "${APT_PACKAGES[@]}"
}

install_asciiquarium() {
  # asciiquarium is not in default Ubuntu repos; needs PPA or snap. :contentReference[oaicite:1]{index=1}
  echo "Installing asciiquarium..."

  # 1) If already installed, do nothing
  if have_cmd asciiquarium; then
    echo "  asciiquarium already installed."
    return
  fi

  # 2) Try via apt in case PPA already exists
  if sudo apt-get install -y asciiquarium 2>/dev/null; then
    echo "  Installed asciiquarium via apt."
    return
  fi

  # 3) Add PPA and install (Ubuntu-specific)
  if have_cmd add-apt-repository; then
    echo "  Trying PPA ppa:ytvwld/asciiquarium ..."
    if sudo add-apt-repository -y ppa:ytvwld/asciiquarium && sudo apt-get update -y; then
      if sudo apt-get install -y asciiquarium; then
        echo "  Installed asciiquarium via PPA."
        return
      fi
    fi
  fi

  # 4) Try snap (unofficial asciiquarium snap) :contentReference[oaicite:2]{index=2}
  if have_cmd snap; then
    echo "  Trying snap install (ASCIIQuarium UNOFFICIAL)..."
    if sudo snap install asciiquarium; then
      echo "  Installed asciiquarium via snap."
      return
    fi
  fi

  echo "WARNING: Could not automatically install asciiquarium."
  echo "         Please install it manually if you want that part of the demo."
}

build_project() {
  if [ -f "$PROJECT_BINARY" ]; then
    echo "Project binary '$PROJECT_BINARY' already exists, skipping build."
    return
  fi

  echo "Building project with: $BUILD_CMD"
  eval "$BUILD_CMD"
  echo "Build complete."
}

### OPTIONAL: DeepSeek (commented out by default) ############################
# Your dependency list includes deepseek-r1:1.5b. The usual way to get that
# on Linux right now is via something like Ollama (ollama.com), which is
# heavy and may not be appropriate to auto-install for your professor.
#
# If you *really* want to automate it, you could uncomment this function and
# call it from main().
#
# install_deepseek() {
#   if ! have_cmd ollama; then
#     echo "Installing Ollama (for deepseek-r1:1.5b)..."
#     curl -fsSL https://ollama.com/install.sh | sh
#   fi
#   echo "Pulling deepseek-r1:1.5b model (this may take a while)..."
#   ollama pull deepseek-r1:1.5b
# }

### MAIN #####################################################################

echo "=== Terminal Simulation Setup ==="

require_apt
apt_install_base_packages
install_asciiquarium
# install_deepseek   # <- leave commented unless you *really* want this

build_project

echo
echo "All done!"
echo "To run the simulation, try:"
echo "  ./$PROJECT_BINARY"
echo
