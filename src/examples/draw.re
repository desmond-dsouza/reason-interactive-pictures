let myViewNew =
  Picture.(picture (300, 300) [Circle (100, 100) 50 Green, Rect (100, 100) 500 20 Red]);

let main: Picture.mainType = Interaction.draw myViewNew;
