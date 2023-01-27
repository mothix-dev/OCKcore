use std::{process::exit, env};
use uname::uname;
use ockcore::get_opts;

fn help() -> ! {
    eprintln!("Usage: uname [-amnrsv]");
    exit(1);
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let args = args.split_at(1).1;
    let opts = get_opts(args, "amnrsv");
    if opts.as_ref().is_none() {help();}
    let info = uname().unwrap();
    if opts.as_ref().unwrap().0.contains('a') {
        println!("{} {} {} {} {}",info.machine,info.nodename,info.release,info.sysname,info.version);
        return;
    }
    if opts.as_ref().unwrap().0.contains('m') {
        print!("{} ",info.machine);
    }
    if opts.as_ref().unwrap().0.contains('n') {
        print!("{} ",info.nodename);
    }
    if opts.as_ref().unwrap().0.contains('r') {
        print!("{} ",info.release);
    }
    if opts.as_ref().unwrap().0.contains('s') || opts.as_ref().unwrap().0.is_empty() {
        print!("{} ",info.sysname);
    }
    if opts.as_ref().unwrap().0.contains('v') {
        print!("{}",info.version);
    }
    println!();
}