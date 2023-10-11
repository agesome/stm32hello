%1\bin\ielfdumparm.exe "%2"\Debug\Exe\ukapp.out -o "%2"\PostBuild\section.txt
%1\bin\ielfdumparm.exe --no-header -s .info_addr "%2"\Debug\Exe\ukapp_its_client.out -o "%2"\PostBuild\info_addr.txt
.\PostBuild\parser.exe .\Debug\Exe\ukapp_its_client.out  .\PostBuild\info_addr.txt  .\PostBuild\section.txt                                                                                         