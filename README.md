# DuckyTypes

A minimal terminal-based typing test inspired by [monkeytype](https://monkeytype.com).

![haha](https://media.discordapp.net/attachments/1040252825495674901/1163399921362276363/image.png?ex=653f6f9c&is=652cfa9c)

## Compatibility

So far only made with linux in mind, untested on macOS and windows (it won't work).

## Building

Once you have `gcc` and `make` installed, simply download the source code and run `make build`.
Alternatively you can grab the latest executable in the release tab.

## Config

After running the program once, a config file is generated. You can edit the following fields:

| Option         | Notes  |
|----------------|----|
| word_list_file | path to the word file, relative to the program. |
| word_size      | size of the words in bytes, 100 should be fine for most cases. |
| test_length    | Number of words in the test. |
| seed           | Used for RNG, 0 for random, used for debugging. |

## Word lists

The default word lists are shamelessly stolen from the [monkeytype github](https://github.com/monkeytypegame/monkeytype), you can put more in the `words` directory. 