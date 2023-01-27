use users::get_current_username;

fn main() {
    match get_current_username() {
        Some(uname) => println!("{}", uname),
        None        => eprintln!("The current user does not exist!"),
    }
}
