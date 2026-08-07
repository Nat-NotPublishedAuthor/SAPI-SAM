# SAPI-SAM
A Windows Text-to-Speech (TTS) wrapper that ports SAM (Software Automatic Mouth) into Microsoft's SAPI (Speech Application Programming Interface). More simply a SAM TTS on Modern Windows.

## What is SAM?
SAM (Software Automatic Mouth) is a small (39 KB to 50 KB) text-to-speech program released in 1982 created by Mark Barton for early personal computers like the Commodore 64, Atari, and Apple II.

An online version to try out can be found on this web site: http://simulationcorner.net/index.php?page=sam (NOT MINE!!!)

## Why do i need this port?
SAM (Software Automatic Mouth) is a very old programm, not compatible with current Windows versions but here you can find a COM DLL that implements Microsoft's SAPI interfaces and routes text through the classic SAM programm, and instructions on how to set it all up.

TL;DR: Cuz SAM cant be a TTS on windows without this.

# Compile

## 1ᵗʰ Step

You'll need to find a port of SAM in EXE format, for that i personally reccommend you check out https://github.com/s-macke/SAM (ALSO NOT MINE!!!).

## 2ⁿᵈ Step
Place the EXE in C:\SAM\sam.exe with SamSapi.dll.

If you want to change the location you must download both dllmain.cpp and sapiddk_compat.h in the folder you want to install them to, then modify line 83 with the path to that folder, after that you will need to download w64devkit (https://github.com/skeeto/w64devkit) (EVEN THIS ISIN'T MINE!!!) and open w64devkit.exe, it will open a terminal where you got to browse to the path with your dllmain.cpp and sapiddk_compat and run:

```g++ -shared -o SamSapi.dll dllmain.cpp -lole32 -luuid -lsapi -loleaut32 -Wl,--add-stdcall-alias -Wl,--defsym,SPDFID_WaveFormatEx=0```

After that in the same path your custom SamSapi.dll will spawn.

(WARNING: sam.exe AND SamSapi.dll MUST BE IN THE PATH YOU CHOSE OR IT WILL NOT FIND THEM.)

## 3ʳᵈ Step

Now open register_sam.reg and apply the changes to the register and after that it'll be installed BUT for some reason you cant select it via the settings so you'll have to make it your default tts, to do that open default_sam.reg and apply the changes to the register.

# WARNING

Just wanna let yall know i vibe coded this, ik it's bad and all but i just wanted the funny blue gopro voice, btw if you can actually select it from the normal settings and other cool things to make this better let me know.

### Tags
ignore. it's just so people find this when they search
windows-sam-tts sam-tts-windows windows-tts-sam sam-speech-windows windows-sam-speech sam-windows-tts tts-windows-sam windows-sapi-sam sam-sapi-windows windows-sam-voice sam-voice-windows windows-sam-wrapper sam-wrapper-windows windows-sam-dll sam-dll-windows windows-sam-synthesizer sam-synthesizer-windows windows-sam-audio sam-audio-windows windows-sam-registry sam-registry-windows windows-retro-sam-tts sam-retro-tts-windows windows-sam-c64-tts sam-c64-tts-windows windows-ultrakill-sam-tts sam-ultrakill-tts-windows windows-sam-speech-api sam-speech-api-windows windows-sam-executable-tts


