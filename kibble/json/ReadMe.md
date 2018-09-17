All json files will contain a "datatype" attribute to identify themselves

## Format
### Unit
A unit file will have the following format  
  
> {   
>   "datatype" : "unit",  
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

Within the data files is an (example)[data/unit/testunit.txt] without tags, ad, sd and size. 
There's also (another example)[data/unit/testunit2.txt] without ad and size.