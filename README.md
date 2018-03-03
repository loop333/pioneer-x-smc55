# pioneer-x-smc55 micro system
Pioneer X-SMC55-S Reverse Engineering

Enable telnet command line interface:  
http://\<ip\>/service_term_sw_nmp.asp  
select TELNET, then Apply  
now you can power off/on and "telnet \<ip\> 9000"

Memory dump:
sys memdump 0x00400000 0x0000fa00  
sys memdump 0x00500000 0x0000fa00  
sys memdump 0x60000000 0x01f00000  
sys memdump 0x71f00000 0x00100000  
