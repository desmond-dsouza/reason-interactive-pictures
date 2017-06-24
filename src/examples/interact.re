open Tea.App;

open Tea.Html;

open Tea.Html.Attributes;

module I = Interaction;

module P = Picture;

type msg =
  | Inc
  | Dec
  | Set int
  | Tick float
  | Slider int
[@@bs.deriving {accessors: accessors}];

let sliderMsg str => Slider (int_of_string str);

type model = Simulate.person;

let initialModel = Simulate.initialPerson;

let update (model: model) (msg: msg) :model =>
  /*Js.log (model, msg);*/
  switch msg {
  | Inc => {...model, base_mood: model.base_mood + 40}
  | Dec => {...model, base_mood: model.base_mood - 40}
  | Set i => {...model, base_mood: i}
  | Tick t => Simulate.updatePerson t model
  | Slider i => {...model, shift: i}
  };

let view model =>
  div
    []
    [
      div [] [text {j| MMModel: $model |j}],
      Simulate.showPerson model,
      button [onClick Inc] [text "+"],
      button [onClick Dec] [text "-"],
      I.slider "Model Shift" 0 200 sliderMsg
    ];

/*let main = beginnerProgram {model: initialModel, update, view};*/
let main: Picture.interactiveDisplay msg =
  Interaction.interact initialModel view update every::(20., tick);
