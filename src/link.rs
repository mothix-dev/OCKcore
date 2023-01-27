use std::{env, process::exit, fs::hard_link};
use ockcore::get_opts;
fn help() -> ! {
    eprintln!("Usage: link [-hv] [file1] [file2] ...");
    eprintln!("Create hard link from file1 to file2");
    eprintln!("Options:");
    eprintln!("\t-h\tshows this message.");
    eprintln!("\t-v\tverbose mode.");
    exit(1);
}

fn main() -> Result<(),std::io::Error> {
    let args: Vec<String> = env::args().collect();
    let args = args.split_at(1).1;
    let opts = get_opts(args, "hv");
    if opts.as_ref().unwrap_or_else(||help()).0.contains('h') {help();}
    let args = &opts.as_ref().unwrap().1;
    match args.len() {
        2 => {
            hard_link(&args[0], &args[1])?;
            if opts.as_ref().unwrap().0.contains('v') {
                println!("{} -> {}", args[0], args[1]);
            }
        }
        _ => help()
    }
    Ok(())
}
