##Basic command line parameter bayan.##

Options:
Required parameters:
  -s [ --scan ] arg       Directory for scanning.

Bayan options:
  -e [ --exclude ] arg    Directory to exclude from scanning. (default empty)
  -D [ --deep ] arg       Deep of scanning. (default 0)
  -m [ --minsize ] arg    Minimal file size to scanning. (default 1Mb)
  -S [ --blocksize ] arg  Size of block. (default 8kb)

Help options:
  -h [ --help ]           Help screen.

Examples:
* 'bayan -s ~ -D1'
* 'bayan -s /home/vasya/games -e /home/vasya/games/coolgame -D2 -m 1024 -S 100000'
