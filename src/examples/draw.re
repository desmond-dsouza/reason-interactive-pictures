let myViewNew =
  Tea.Html.(
    Picture.(
      div
        []
        [
          h1 [] [text "A drawing"],
          picture (300, 300) [Circle (100, 100) 50 Pink, Rect (100, 100) 500 20 Red],
          div [] [text "below the first picture"]
        ]
    )
  );

let main: Picture.mainType = Interaction.draw myViewNew;
