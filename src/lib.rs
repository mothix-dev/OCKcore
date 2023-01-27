use libc::ttyname;
use std::ffi::CStr;
/// This function assumes you removed the executable name from the arguments.
#[must_use]
pub fn get_opts(args: &[String], switches: &str) -> Option<(String,Vec<String>)> {
    let mut opts = String::new();
    let mut end = 0;
    for arg in args {
        match arg.as_str() {
            "--" => {
                end+=1;
                break;
            },
            "-" => break,
            s if arg.starts_with('-') => {
                opts.push_str(s.split_at(1).1);
                end += 1;
            },
            _ => break
        }
    }
    if opts.chars().all(|c| switches.contains(c)) {
        Some((opts,args.split_at(end).1.to_vec()))
    } else {
        None
    }
}

/// # Errors
/// Whatever errno might be.
/// # Safety
/// There is a chance `libc::__errno_location()` might be wrong. Plus, this does many unsafe things anyways.
pub unsafe fn tty_name() -> Result<String, i32> {
    let name_ptr = ttyname(libc::STDIN_FILENO);
    if name_ptr.is_null() {
        return Err(*(libc::__errno_location()))
    }
    let name = CStr::from_ptr(name_ptr).to_string_lossy().into_owned();
    Ok(name)
}