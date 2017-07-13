module H = Tea.Html;

module P = Picture;

let lorem = {|Lorem ipsum blah, Lorem ipsum blah,
    Lorem ipsum blah, Lorem ipsum blah, Lorem ipsum blah.
    Lorem ipsum blah Lorem ipsum blah Lorem ipsum blah.|};

let view =
  H.div
    []
    [
      P.stylesheet P.cssBulmaUrl,
      H.div
        [H.class' "columns"]
        [
          H.div
            [H.class' "column is-three-quarters box"]
            [H.h1 [] [H.text "col1"], Draw.showPerson Draw.initialPerson],
          H.div [H.class' "column box"] [H.h1 [] [H.text "col2"], H.text lorem]
        ]
    ];

let main: Picture.simpleDisplay = Interaction.draw view;
