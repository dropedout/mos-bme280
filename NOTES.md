# Handling mos tool

Use local built tool sometime give error during local and remote build execution.

## issue: broken mos tool
[micha@sonstwo mos-bme280]$ mos build
fatal error: unexpected signal during runtime execution
[signal 0xb code=0x1 addr=0x47 pc=0xc6602c66]

runtime stack:
runtime.throw(0x889f720, 0x2a)
	/usr/lib/go-1.6/src/runtime/panic.go:547 +0x7f
runtime.sigpanic()
	/usr/lib/go-1.6/src/runtime/sigpanic_unix.go:12 +0x59

goroutine 5 [syscall, locked to thread]:

### Fix 1

found on [cesante github issue 297](https://github.com/cesanta/mongoose-os/issues/297)

{{{
cd $GOPATH/src/cesanta.com
git pull

# remove all vendored packages
rm -r $(find vendor -maxdepth 1 -mindepth 1 -type d)

# remove all Go sources other than cesanta.com (assuming you don't have anything valuable there)
rm -r $(find $GOPATH/src -maxdepth 1 -mindepth 1 -type d -not -name cesanta.com)

govendor sync

cd mos
go generate
go build
}}}


