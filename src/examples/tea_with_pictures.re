open Tea.App;

open Tea.Html;

module I = Interaction;

module P = Picture;

type msg =
  | Inc
  | Dec
  | Set int;

let init = 2;

let update model msg =>
  switch msg {
  | Inc => model + 1
  | Dec => model - 1
  | Set i => i
  };

let view model => {
  let rec range i j => i > j ? [] : [i, ...range (i + 1) j];
  let circles = List.map (fun i => P.Circle (100 + 40 * i, 100) 15 Blue) (range 1 model);
  module S = Tea.Svg;
  module SA = Tea.Svg.Attributes;
  div
    []
    [
      P.picture (300, 300) circles,
      button [onClick Inc] [text "+"],
      button [onClick Dec] [text "-"],
      S.svg
        [SA.width "100px", SA.height "100px"]
        [
          S.circle
            [
              SA.cx "10",
              SA.cy "10",
              SA.r "10",
              SA.fill "Black",
              Tea.Html.onClick Inc,
              Tea.Html.style "cursor" "pointer"
            ]
            []
        ],
      Animate.myView 45.0
    ]
};

let main = beginnerProgram {model: init, update, view};
