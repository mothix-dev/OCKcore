use std::{process::exit, env};
use ockcore::get_opts;
fn help() -> ! {
    eprintln!("Usage: pwd [-LPh]");
    eprintln!("Print working directory.");
    eprintln!("Defaults to relative path.");
    eprintln!("Options:");
    eprintln!("\t-L\trelative path.");
    eprintln!("\t-P\tabsolute path.");
    eprintln!("\t-h\tshows this message.");
    exit(1);
}

fn main() -> Result<(),std::io::Error> {
    let args: Vec<String> = env::args().collect();
    let args = args.split_at(1).1;
    let path = env::current_dir()?;
    let opts = get_opts(args, "LPh");
    if opts.as_ref().unwrap_or_else(||help()).0.contains('h') {help();}
    if opts.unwrap().0.ends_with('P') {
        println!("{}",path.canonicalize()?.display());
    } else {
        println!("{}",path.display());
    }
    Ok(())
}