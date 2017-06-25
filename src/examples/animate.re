let showPersonAt (t: float) => {
  let delta = 120. *. sin (t /. 250.) |> int_of_float;
  let p' = Interaction.debug "p': " {...Draw.initialPerson, Draw.shift: delta};
  Draw.showPerson p'
};

let main: Picture.simpleDisplay = Interaction.animate showPersonAt delta_ms::5.0;
