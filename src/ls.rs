use std::{process::exit, env, path::{PathBuf, Path}};
use ockcore::get_opts;

fn help() -> ! {
    eprintln!("Usage: ls [-1ha] <directory>");
    exit(1);
}

fn main() -> Result<(), std::io::Error> {
    let args: Vec<String> = env::args().collect();
    let args = args.split_at(1).1;
    let mut one_per_line = false;
    let mut show_hidden = false;
    let opts = get_opts(args, "1ha");
    if opts.as_ref().unwrap_or_else(||help()).0.contains('h') {help();}
    if opts.as_ref().unwrap().0.contains('1') {
        one_per_line = true;
    }
    if opts.as_ref().unwrap().0.contains('a') {
        show_hidden = true;
    }
    let args = opts.unwrap().1;
    if args.is_empty() {
        ls(&env::current_dir()?, one_per_line, show_hidden);
    } else {
        for arg in args {
            ls(&PathBuf::from(arg), one_per_line, show_hidden);
        }
    }
    Ok(())
}

fn ls(pb: &Path, one_per_line: bool, show_hidden: bool) {
    for entry in pb.read_dir().expect("could not read directory").flatten() {
        if show_hidden || !entry.file_name().to_str().unwrap().starts_with('.') {
            if one_per_line {
                println!("{}", entry.file_name().to_str().unwrap());
            } else {
                print!("{} ", entry.file_name().to_str().unwrap());
            }
        }
    }
}