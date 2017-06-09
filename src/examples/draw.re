let myViewNew =
  Tea.Html.div
    []
    [
      Tea.Html.h1 [] [Tea.Html.text "A drawing"],
      Picture.(picture (300, 300) [Circle (100, 100) 50 Pink, Rect (100, 100) 500 20 Red]),
      Tea.Html.(div [] [text "below the first picture"])
    ];

let main: Picture.mainType = Interaction.draw myViewNew;
