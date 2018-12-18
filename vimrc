" General settings
set number
set relativenumber
set tabstop=4
set shiftwidth=4
set softtabstop=4
set expandtab
set cc=90
set autoindent
set background=dark
set mouse=a
set noswapfile

" Aliases for arrow keys
map <ESC>OC <right>
map <ESC>OD <left>
map <ESC>OA <up>
map <ESC>OB <down>
map <ESC>[1;[5D <C-left>
map <ESC>[1;[5C <C-right>

" Movement
map <A-Up> <Up><Up><Up><Up><Up><Up><Up><Up><Up><Up>
imap <A-Up> <Up><Up><Up><Up><Up><Up><Up><Up><Up><Up>

map <A-Down> <Down><Down><Down><Down><Down><Down><Down><Down><Down><Down>
imap <A-Down> <Down><Down><Down><Down><Down><Down><Down><Down><Down><Down>
       
map <A-Left> <Left><Left><Left><Left><Left><Left><Left><Left><Left><Left>
imap <A-Left> <Left><Left><Left><Left><Left><Left><Left><Left><Left><Left>
       
map <A-Right> <Right><Right><Right><Right><Right><Right><Right><Right><Right><Right><Right>
imap <A-Right> <Right><Right><Right><Right><Right><Right><Right><Right><Right><Right><Right>
       
map <C-Up> <Up><Up><Up><Up><Up><Up><Up><Up><Up><Up>
imap <C-Up> <Up><Up><Up><Up><Up><Up><Up><Up><Up><Up>

map <C-Down> <Down><Down><Down><Down><Down><Down><Down><Down><Down><Down>
imap <C-Down> <Down><Down><Down><Down><Down><Down><Down><Down><Down><Down>
 
" TODO: Fix conflict with tabs
"map <C-Left> <Left><Left><Left><Left><Left><Left><Left><Left><Left><Left>
"imap <C-Left> <Left><Left><Left><Left><Left><Left><Left><Left><Left><Left>

"map <C-Right> <Right><Right><Right><Right><Right><Right><Right><Right><Right><Right><Right>
"imap <C-Right> <Right><Right><Right><Right><Right><Right><Right><Right><Right><Right><Right>

" Tabs
map <C-w> :q <CR>
imap <C-w> <ESC>:q <CR>i

map <C-t> :tabnew<CR>i
imap <C-t> <ESC>:tabnew<CR>i 

map <C-left> :tabprev<CR>
imap <C-left> <ESC>:tabprev<CR>i

map <C-right> :tabnext<CR>
imap <C-right> <ESC>:tabnext<CR>i

" Navigating wrapped lines
noremap <up> g<up>
noremap <down> g<down>

" C/C++ compilation and running
autocmd FileType c    setlocal makeprg=gcc\ -g\ -O2\ -Wall\ %\ -o\ _%<\ -lm
autocmd FileType cpp  setlocal makeprg=g++\ -std=c++14\ -O2\ -Wall\ %\ -o\ _%<\ -lm
autocmd FileType c,cpp  map <buffer> <F9> :w<CR>:!clear<CR>:make!<CR>:!echo --------------------------------------------------------------------------------<CR>:!time ./_%< <CR>
autocmd FileType c,cpp imap <buffer> <F9> :w<CR>:!clear<CR>:make!<CR>:!echo --------------------------------------------------------------------------------<CR>:!time ./_%< <CR>

" Java compilation and running
autocmd FileType java setlocal makeprg=javac\ %
autocmd Filetype java   map <buffer> <F9> :w<CR>:!clear<CR>:make!<CR>:!echo --------------------------------------------------------------------------------<CR>:!java %:r <CR>
autocmd Filetype java  imap <buffer> <F9> :w<CR>:!clear<CR>:make!<CR>:!echo --------------------------------------------------------------------------------<CR>:!java %:r <CR>

" Python running
autocmd FileType python map <buffer> <F9> :w<CR>:!clear<CR>:!time python3 % <CR>

" Bash   running
autocmd FileType bash,sh map <buffer> <F9> :w<CR>:!clear<CR>:!time ./% <CR>
