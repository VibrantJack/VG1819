## Format
### Unit
A unit file will have the following format  
  
> {     
>   "name" : "",  
>   "hp" : ,  
>   "mv" : ,  
>   "in" : ,  
>   "cost" : ,  
>   "size" : "",   
>   "tags" : [ ],  
>   "ad" : [ ],  
>   "sd" : [ ],  
> }
  
The size attribute is optional. By default it will assign a cube size.  
If however it is inputted and theres anything other than "cube" value, it will assign it as a point.  
  
Tags are also optional, and would be filled in as an array of string values.

ad short for ability description, and is optional. Needs an array of string values.

sd short for status description, and is optional. Needs an array of strings values.

Within the data files is an (example) [data/unit/testunit.txt] without tags, ad, sd and size. 
There's also (another example) [data/unit/testunit2.txt] without ad and size.

### Unit List
A unit list file will have the following format  

> {  
>    "units" : [  
>       {  
>           "name" : "", ...  
>       },  
>       {  
>           "name" : "", ...  
>       }, ...  
>   ]  
> }  

All it is, is an array of Units of the past format. 
This follows the same exact rules as the Unit format. 