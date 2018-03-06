# pioneer-x-smc55 micro system
Pioneer X-SMC55-S Reverse Engineering

Enable telnet command line interface:  
http://\<ip\>/service_term_sw_nmp.asp  
select TELNET, then Apply  
now you can power off/on and "telnet \<ip\> 9000"

Memory dump:  
sys memdump 0x00400000 0x0000fa00 ; system code  
sys memdump 0x00500000 0x0000fa00 ; same as 0x00400000 but non-cached  
sys memdump 0x60000000 0x0aa80000 ; code  
sys memdump 0x60aa8000 0x01458000 ; stack  
sys memdump 0x71f00000 0x00100000 ; stack  

Firmware file decryption looks like Blowfish, but password and initialization vector from dump didn't match maybe non-standard s-boxes
