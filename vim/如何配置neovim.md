# 如何配置neovim

## 我的init.vim

```bash
call plug#begin('~/.AppData/local/nvim/plugged') "Vim 插件的安装路径，可以自定义。
"~ 表示系统路径，在windows下为 C:/User/username/

"Plug 'path/of-plugin'
Plug 'morhetz/gruvbox'
Plug 'vim-scripts/vim-airline'
Plug 'vim-scripts/Tagbar'
Plug 'plasticboy/vim-markdown'
Plug 'neoclide/coc.nvim'
Plug 'nvim-treesitter/nvim-treesitter'
Plug 'ferrine/md-img-paste.vim'
Plug 'godlygeek/tabular'
Plug 'plasticboy/vim-markdown'
Plug 'iamcco/markdown-preview.nvim', { 'do': { -> mkdp#util#install() }, 'for': ['markdown', 'vim-plug']}
Plug 'preservim/nerdtree'
Plug 'yuttie/inkstained-vim'
Plug 'nvim-lua/plenary.nvim'
Plug 'nvim-telescope/telescope.nvim'
Plug 'kyazdani42/nvim-web-devicons'
Plug 'nvim-treesitter/nvim-treesitter', {'do': ':TSUpdate'}
Plug 'KeitaNakamura/neodark.vim'
Plug 'vim-scripts/easymotion'
"将所有插件安装在这里

call plug#end()
"My settings begin
set relativenumber
imap jj <esc>
set clipboard+=unnamed
let leader=' '
set easymotion
"My settings end

colorscheme gruvbox
set background=dark
let g:vim_markdown_folding_disabled = 1
map <F2> :NERDTree<CR>
map <F2> :NERDTreeToggle<CR>
" for normal mode
nmap  <F8> <Plug>MarkdownPreview
" for insert mode
imap <silent> <F8> <Plug>MarkdownPreview
" for normal mode
nmap <leader> <F9> <Plug>StopMarkdownPreview
" for insert mode
imap <silent> <F9> <Plug>StopMarkdownPreview

" Find files using Telescope command-line sugar.
autocmd FileType markdown nmap <buffer><silent> <leader>i :call mdip#MarkdownClipboardImage()<CR>
let g:mdip_imgdir = '.'
let g:mdip_imgname = 'image'
highlight Normal guibg=NONE ctermbg=None
set cursorline
"hi CursorLine ctermbg=darkgrey
set cursorcolumn
set autoindent
set wrap
set nu
set tabstop=4
set shiftwidth=2
set expandtab
set fileencodings=gb18030,gbk,gb2312,utf-8
set termencoding=utf-8
set incsearch " incremental search
set laststatus=2 
set list lcs=tab:\|\ 
syntax enable

```

