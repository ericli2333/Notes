#! https://zhuanlan.zhihu.com/p/614078727
# 如何配置neovim

## 我的init.vim

```bash
call plug#begin('~/.AppData/local/nvim/plugged') "Vim 插件的安装路径，可以自定义。
"~ 表示系统路径，在windows下为 C:/User/username/

"Plug 'path/of-plugin'
" for markdown begin
Plug 'godlygeek/tabular' 
Plug 'plasticboy/vim-markdown'
Plug 'mzlogin/vim-markdown-toc'
Plug 'iamcco/markdown-preview.nvim', { 'do': 'cd app && yarn install' }
Plug 'SirVer/ultisnips'
" for markdown end

Plug 'lervag/vimtex'

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
"My settings end

"For latex begin
let g:tex_flavor = 'latex'
let g:vimtex_quickfix_mode = 0 
"将编译报错自动弹出错误窗口（quickfix window）设置为 0（即不自动弹出）。我们可以使用命令 :copen 来手动打开错误窗口
let g:vimtex_view_general_viewer = 'SumatraPDF'
let g:vimtex_view_general_options
\ = '-reuse-instance -forward-search @tex @line @pdf'
let g:vimtex_view_general_options_latexmk = '-reuse-instance'
let g:vimtex_toc_config = {
\ 'name' : 'TOC',
\ 'layers' : ['content', 'todo', 'include'],
\ 'split_width' : 25,
\ 'todo_sorted' : 0,
\ 'show_help' : 1,
\ 'show_numbers' : 1,
\}
"For latex end

colorscheme gruvbox
set background=dark
let g:vim_markdown_folding_disabled = 1
map <F2> :NERDTree<CR>
map <F2> :NERDTreeToggle<CR>
" for normal mode
nmap <silent> <F8> <Plug>MarkdownPreview

" for normal mode
nmap <silent> <F9> <Plug>StopMarkdownPreview

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

" for markdown begin
let g:vim_markdown_math = 1
"设置tagber对于markdown的支持
let g:tagbar_type_markdown = {
    \ 'ctagstype' : 'markdown',
    \ 'kinds' : [
        \ 'h:Chapter',
        \ 'i:Section',
        \ 'k:Paragraph',
        \ 'j:Subparagraph'
    \ ]
\ }
"取消显示section_b
let g:airline_section_b = ''
"section_c显示为tagbar检索出来的标题
let g:airline_section_c = airline#section#create(['tagbar'])
"section_x显示文件名
let g:airline_section_x = '%{expand("%")}'
"section_y显示时间
let g:airline_section_y = airline#section#create(['%{strftime("%D")}'])
"section_z显示日期
let g:airline_section_z = airline#section#create(['%{strftime("%H:%M")}'])
"激活tagbar扩展
let g:airline#extensions#tagbar#enabled = 1


"配置预览
" set to 1, nvim will open the preview window after entering the markdown buffer
" default: 0
let g:mkdp_auto_start = 0

" set to 1, the nvim will auto close current preview window when change
" from markdown buffer to another buffer
" default: 1
let g:mkdp_auto_close = 1

" set to 1, the vim will refresh markdown when save the buffer or
" leave from insert mode, default 0 is auto refresh markdown as you edit or
" move the cursor
" default: 0
let g:mkdp_refresh_slow = 0

" set to 1, the MarkdownPreview command can be use for all files,
" by default it can be use in markdown file
" default: 0
let g:mkdp_command_for_global = 0

" set to 1, preview server available to others in your network
" by default, the server listens on localhost (127.0.0.1)
" default: 0
let g:mkdp_open_to_the_world = 0

" use custom IP to open preview page
" useful when you work in remote vim and preview on local browser
" more detail see: https://github.com/iamcco/markdown-preview.nvim/pull/9
" default empty
let g:mkdp_open_ip = ''

" specify browser to open preview page
" for path with space
" valid: `/path/with\ space/xxx`
" invalid: `/path/with\\ space/xxx`
" default: ''
let g:mkdp_browser = ''

" set to 1, echo preview page url in command line when open preview page
" default is 0
let g:mkdp_echo_preview_url = 0

" a custom vim function name to open preview page
" this function will receive url as param
" default is empty
let g:mkdp_browserfunc = ''

" options for markdown render
" mkit: markdown-it options for render
" katex: katex options for math
" uml: markdown-it-plantuml options
" maid: mermaid options
" disable_sync_scroll: if disable sync scroll, default 0
" sync_scroll_type: 'middle', 'top' or 'relative', default value is 'middle'
"   middle: mean the cursor position alway show at the middle of the preview page
"   top: mean the vim top viewport alway show at the top of the preview page
"   relative: mean the cursor position alway show at the relative positon of the preview page
" hide_yaml_meta: if hide yaml metadata, default is 1
" sequence_diagrams: js-sequence-diagrams options
" content_editable: if enable content editable for preview page, default: v:false
" disable_filename: if disable filename header for preview page, default: 0
let g:mkdp_preview_options = {
    \ 'mkit': {},
    \ 'katex': {},
    \ 'uml': {},
    \ 'maid': {},
    \ 'disable_sync_scroll': 0,
    \ 'sync_scroll_type': 'middle',
    \ 'hide_yaml_meta': 1,
    \ 'sequence_diagrams': {},
    \ 'flowchart_diagrams': {},
    \ 'content_editable': v:false,
    \ 'disable_filename': 0,
    \ 'toc': {}
    \ }

" use a custom markdown style must be absolute path
" like '/Users/username/markdown.css' or expand('~/markdown.css')
let g:mkdp_markdown_css = ''

" use a custom highlight style must absolute path
" like '/Users/username/highlight.css' or expand('~/highlight.css')
let g:mkdp_highlight_css = ''

" use a custom port to start server or empty for random
let g:mkdp_port = ''

" preview page title
" ${name} will be replace with the file name
let g:mkdp_page_title = '「${name}」'

" recognized filetypes
" these filetypes will have MarkdownPreview... commands
let g:mkdp_filetypes = ['markdown']

" set default theme (dark or light)
" By default the theme is define according to the preferences of the system
let g:mkdp_theme = 'dark'
"配置预览结束
"snipper begin
"设置tab键为触发键
let g:UltiSnipsExpandTrigger = '<tab>'
"设置向后跳转键
let g:UltiSnipsJumpForwardTrigger = '<tab>' 
"设置向前跳转键
let g:UltiSnipsJumpBackwardTrigger = '<S-tab>' 
"设置文件目录
let g:UltiSnipsSnippetDirectories=["path/of/snippetDirectories"]
"设置打开配置文件时为垂直打开
let g:UltiSnipsEditSplit="vertical"
"snipper end


" for markdown end

```

