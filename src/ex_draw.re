module S = Tea.Svg;

module SA = Tea.Svg.Attributes;

let myViewNew: Vdom.t Interaction.msg =
  Picture.(
    S.svg
      [SA.width "300px", SA.height "300px"]
      [Circle (100, 100) 50 "green" |> render, Rect (100, 100) 500 20 "red" |> render]
  );

let main: Js.null_undefined Web.Node.t => unit => Tea.App.programInterface Interaction.msg =
  Interaction.draw myViewNew;
