use std::process::exit;
use users::get_current_username;

fn main() {
    if let Some(u) = get_current_username() {
        println!("{}", u.to_str().unwrap());
    } else {
        eprintln!("The current user does not exist!");
        exit(-1);
    }
}
