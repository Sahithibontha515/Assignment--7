let mean lst =
  let sum = List.fold_left ( + ) 0 lst in
  float_of_int sum /. float_of_int (List.length lst)


let median lst =
  let sorted = List.sort compare lst in
  let n = List.length sorted in
  if n mod 2 = 1 then
    float_of_int (List.nth sorted (n / 2))
  else
    let a = List.nth sorted (n / 2 - 1) in
    let b = List.nth sorted (n / 2) in
    (float_of_int (a + b)) /. 2.0


let mode lst =

  let freq =
    List.fold_left (fun acc x ->
      let count = try List.assoc x acc + 1 with Not_found -> 1 in
      (x, count) :: List.remove_assoc x acc
    ) [] lst
  in

  let max_count =
    List.fold_left (fun m (_, c) -> if c > m then c else m) 0 freq
  in

  freq
  |> List.filter (fun (_, c) -> c = max_count)
  |> List.map fst


let () =
  (* Prompt & read *)
  Printf.printf "Enter integers separated by spaces:\n%!";
  let line = read_line () in
  (* Split on spaces, convert to int *)
  let data = 
    String.split_on_char ' ' line
    |> List.filter ((<>) "")
    |> List.map int_of_string
  in


  let m    = mean data in
  let med  = median data in
  let mods = mode data in


  Printf.printf "\nMean:   %.2f\n" m;
  Printf.printf "Median: %.2f\n" med;
  Printf.printf "Mode%s: %s\n"
    (if List.length mods > 1 then "s" else "")
    (String.concat ", " (List.map string_of_int mods))
