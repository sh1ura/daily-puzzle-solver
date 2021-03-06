# "Daily puzzle" solver

## A Solver of "a-puzzle-a-day" and its my own variants

<a href="https://www.dragonfjord.com/product/a-puzzle-a-day/">A-puzzle-a-day</a> is truly genius and I like it, but it seems too difficult for children (and, to be honest, for me too). However, the design of the puzzle is <a href="https://euipo.europa.eu/eSearch/#details/designs/007690433-0001">registered to the intellectual property office</a>, and minor modification might still infringe their rights. Therefore I designed thoroughly modified version from scratch. 

My design, named "Daily puzzle", has month and date cells mixed together. Additionally, six wildcard cells `*` are placed to simplify the shape of the base board. I prepared four types of piece sets with various difficulties (different number of pieces). 

I confirmed there are at least one solution for each month/date combination using solver programs. The solver is also capable of original "A-puzzle-a-day". All solutions (results of the solver) are also provided.

I just make the idea of the puzzle public, but no 3D data of the puzzle now. I recommend [Daily Hexagonal Puzzle](https://github.com/sh1ura/daily-hex-puzzle) because of the more strict originarity.

![daily-puzzle-ss](https://user-images.githubusercontent.com/86639425/159103329-bf56ae79-b869-4954-9d91-f7f9315971f6.jpg)


## Number of pieces and difficulties

![table](https://user-images.githubusercontent.com/86639425/159051443-4f6d26db-561e-4b1d-aa51-2a7211339764.jpg)

At first, I thought that the fewer and larger pieces make the puzzle more difficult. However, after some trials, I found that this relationship is not so clear. In fact, as shown above, the more pieces we have, the more solutions exist. However, the number of possible arrangements also increases, and it makes the puzzle more difficult. At least, 11 pieces version is clearly the easiest, but the other three versions are not so different I think.

## My puzzle design

![board](https://user-images.githubusercontent.com/86639425/158950665-af8fa557-0c32-4527-920a-d254e974150f.jpg)
Common board for all types of piece sets

![hard](https://user-images.githubusercontent.com/86639425/158950682-ddb1d5e4-0a4f-450e-8514-19d92df3a5a9.jpg)
8 pieces

![normal](https://user-images.githubusercontent.com/86639425/158950692-47c8c975-4c2c-47fc-9539-d96d46da1e83.jpg)
9 pieces

![easy](https://user-images.githubusercontent.com/86639425/158950705-24bc20ed-8f18-4967-8a2a-0ec41a364802.jpg)
10 pieces

![very-easy](https://user-images.githubusercontent.com/86639425/158950716-4e12fa6f-8919-4f75-88bc-c94546e5d21f.jpg)
11 pieces, the easiest version
