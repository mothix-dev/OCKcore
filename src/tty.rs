use std::process::exit;
use ockcore::tty_name;
fn main() {
    match unsafe{tty_name()} {
        Ok(name) => println!("{name}"),
        Err(libc::ENOTTY) => {
            eprintln!("not a tty");
            exit(1);
        }
        Err(no) => {
            eprintln!("error");
            exit(no);
        }
    }
}