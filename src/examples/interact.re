module H = Tea.Html;

module Simulate = Simulate;

/* *********** Model ******* */
type model = {
  person: Simulate.person,
  simRate: int
};

/* *********** Messages ******* */
type msg =
  | Inc
  | Dec
  | SetShift int
  | Tick float
  | SetSimRate int
[@@bs.deriving {accessors: accessors}];

/* *********** View ******* */
let view {person, simRate} =>
  H.div
    []
    [
      H.div [] [H.text {j| Model :: Simulation Rate: $person :: $simRate |j}],
      H.button [H.onClick Inc] [H.text "Inc Base_Mood"],
      H.button [H.onClick Dec] [H.text "Dec Base_Mood"],
      Interaction.slider "Model Shift (slider)" 0 200 setShift,
      Interaction.selector "Model Shift (select)" [0, 20, 50, 100, 200] setShift,
      Interaction.slider "Simulation Rate" 1 10 setSimRate,
      Simulate.showPerson person
    ];

/* *********** Update ******* */
let update (model: model) (msg: msg) :model =>
  /*Js.log (model, msg);*/
  switch msg {
  | Inc => {...model, person: {...model.person, base_mood: model.person.base_mood + 40}}
  | Dec => {...model, person: {...model.person, base_mood: model.person.base_mood - 40}}
  | SetShift i => {...model, person: {...model.person, shift: i}}
  | Tick t => {
      ...model,
      person: Simulate.updatePerson (t *. float_of_int model.simRate /. 10.) model.person
    }
  | SetSimRate i => {...model, simRate: i}
  };

/* *********** Initialize ******** */
let initialModel = {person: Simulate.initialPerson, simRate: 1};

/*let main = beginnerProgram {model: initialModel, update, view};*/
let main: Picture.interactiveDisplay msg =
  Interaction.interact initialModel view update every::(20., tick);
