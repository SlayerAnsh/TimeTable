# TIME TABLE ALGORITHM

  Time Table algorithm for our university with many flexible features and super fast.

### Input Format
- First line contains three space separated integers `Days` `Slots` `Slot Duration`
- Second line contains number of rooms available `Num_Rooms`
- Next `Num_Rooms` line contain two space separated values `Room Id` and `Room Size`
- Next line contains one integer denoting number lunch/openelective slots `Num_Lunch_Slots`
- next line contains `Num_Lunch_Slots` space separated integers denoting slots of lunch/open-elective.
- Next line contains number of courses `Num Courses`. Courses are CSE 1st Year ME 2nd Year etc.
- Next Lines contain course detail in this format `Course Code` `Number of Subjects in the course` `Number of Groups in the Batch` `Size of Batch` `has open ELective`
- For each Course we have `Number of Subjects in the Course` lines which contain following information in the same order `Subject Code` `Faculty Code` `Is Lab?` `Number of Lectures` `Number of Tutorials` `Duration of Each Class` `Number of Room Preferences`

### Some General Points about the inputs:
- `is Lab?` and `has Open Electives` are boolean values where 1 is true and 0 is false.
- `Number of Room Preferences` is greater than 0 then room will be alloted only from the preferences. Which means if no room is free from preferences then the subject wont be alloted any room even though some other room may be availbale.
- `Number of Room Preferences` is arranged in high to low priority. That is room mentioned first will be given higher priority.
- `Room Size` should be maxmimum possible size of room. That is if room size is 100 then it means that room can accomodate at max 100 students (maximum crowded)

### Features:
- Highly flexible with time slots.
- Generates correct time table for more than 2 groups (increase in size of new batches really need this feature)
- Efficient Room Distributer (Small Batch size will get room with small room size)
- Can include features like pre-occupied slots.
- Super Fast
- Easy to Debug
- Generate Different Files for each view (Class, Faculty, Room)
- Room preference for each class
- Zero clash gaurantee
- Easily integradable with other algorithms (which i will include in near future)
- Easily Modified with need.
- Multiple Time Table Generator.
