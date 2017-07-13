module H = Tea.Html;

module Simulate = Simulate;

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
  | Set i => {...model, shift: i}
  | Tick t => Simulate.updatePerson t model
  | Slider i => {...model, shift: i}
  };

let view model =>
  H.div
    []
    [
      H.div [] [H.text {j| Model: $model |j}],
      H.button [H.onClick Inc] [H.text "Inc Base_Mood"],
      H.button [H.onClick Dec] [H.text "Dec Base_Mood"],
      Interaction.slider "Model Shift" 0 200 sliderMsg,
      Interaction.selector "Model Shift Select" [0, 20, 50, 100, 200] set,
      Simulate.showPerson model
    ];

/*let main = beginnerProgram {model: initialModel, update, view};*/
let main: Picture.interactiveDisplay msg =
  Interaction.interact initialModel view update every::(20., tick);
