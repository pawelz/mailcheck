# mailcheck

## Synopsis

mailcheck is a simple tool checking the number of new mail in a maildir.

It is intended to be run from ~/.profile, so that the user gets notified about
new email on login.

## Usage

```sh
$ mailcheck [flags] <Maildir path relative to ~> <maildir> [<maildir> <maildir> ...]
```

For example if you keep your email in ~/Maildir/INBOX, ~/Maildir/spam and
~/Maildir/blackmail, the correct invocation would be:

```sh
$ mailcheck Maildir INBOX spam blackmail
```

Flags:

* `-d` or `--debug`: litters output with extra debugging information
* `-h` or `--help`: prints a usage message and exits

## No robots

No robots were harmed in making of this code. It was lovingly handcrafted by
a human with help from the Linux man pages.
