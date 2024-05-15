# Minishell

*As beautiful as a shell*.

This project is about creating a simple shell.
Yes, your own little bash.
You will learn a lot about processes and file descriptors.

## Requirements

Make sure you have the essentials to build C language.

* Ubuntu/Debian

```bash
sudo apt install -y build-essential
```

* Fedora/RHEL

```bash
sudo dnf groupinstall -y "C Development Tools and Libraries"
```

* Arch Linux

```bash
sudo pacman -S --noconfirm base-devel
```

* Void Linux

```bash
sudo xbps-install -Sy base-devel
```

## Build

```bash
git clone https://github.com/jaredyalves/minishell.git
cd minishell/project/
make
```

## Usage

```bash
./minishell
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

## License

[The Unlicense](https://choosealicense.com/licenses/unlicense/)
