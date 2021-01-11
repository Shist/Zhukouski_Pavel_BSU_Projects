#ifndef _LAB_1_DNS_H_
#define _LAB_1_DNS_H_

typedef   unsigned int DNSHandle;
typedef   unsigned int IPADDRESS;

#define   INVALID_DNS_HANDLE   0
#define   INVALID_IP_ADDRESS   0     // 0.0.0.0


/*************************************************************************
 FUNCTION: 
    InitDNS()             

 DESCRIPTION:
    Initializes DNS engine

 PARAMETERS:
    None

 RETURN VALUE:
    Handle of DNS engine on success, or INVALID_DNS_HANDLE on error.
	This haandle will be used by other functions to identify DNS engine
	to work with.
************************************************************************/
DNSHandle InitDNS( );









/*************************************************************************
 FUNCTION: 
    LoadHostsFile()             

 DESCRIPTION:
    Loads DN information from the file and adds it to the DN engine specified
    by hDNS param

 PARAMETERS:
    hDNS: DNSHandle - valid handle of DNS engine returned by InitDNS() 
    function
    hostsFilePath: const char* - path of the file which contains DN - IP
    correspondence

 RETURN VALUE:
    None
************************************************************************/
void LoadHostsFile( DNSHandle hDNS, const char* hostsFilePath );








/*************************************************************************
 FUNCTION: 
    ShutdownDNS()             

 DESCRIPTION:
    Shuts down DNS engine and release all its resources

 PARAMETERS:
    hDNS: DNSHandle - valid handle of DNS engine returned by InitDNS() 
    function

 RETURN VALUE:
    None.

 NOTE:
    After this call the DNS handle passed to the functions is invalid
************************************************************************/
void ShutdownDNS( DNSHandle hDNS );







/*************************************************************************
 FUNCTION: 
    DnsLookUp()             

 DESCRIPTION:
    Performs DN Look up in the DN engine specified

 PARAMETERS:
    hDNS: DNSHandle - valid handle of DNS engine returned by InitDNS() 
    function
    hostName: const char* - name of a host

 RETURN VALUE:
    IP address of the host specified or INVALID_IP_ADDRESS for unknown
    host
	
 EXAMPLE:
    hostName = "localhost" -> return value == 0x7F000001 (127.0.0.1)
************************************************************************/
IPADDRESS DnsLookUp( DNSHandle hDNS, const char* hostName );




#endif // _LAB_1_DNS_H_