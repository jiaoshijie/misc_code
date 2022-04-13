local _M = {}
local findstar = require('undotree.utils').findstar
local bufname = 'jsj_undotree_1'

local time_ago = function(ptime)
  local sec = vim.fn.localtime() - ptime
  local mf = math.floor
  if sec < 60 then
    return mf(sec) .. ' seconds ago'
  elseif sec < 3600 then
    return mf(sec / 60) .. ' minutes ago'
  elseif sec < 86400 then
    return mf(sec / 3600) .. ' hours ago'
  end
  return mf(sec / 86400) .. ' days ago'
end

local graph2buf = function(bufnr, cGraph, asciimeta)
  vim.api.nvim_buf_set_option(bufnr, 'modifiable', true)
  -- clear the buf
  if vim.fn.bufnr() ~= bufnr then
    vim.cmd(string.format('silent exe "%s"', "norm! " .. vim.fn.bufwinnr(bufnr) .. "\\<c-w>\\<c-w>"))
  end
  vim.cmd[[exe '1,$ d _']]
  local i = 0
  while i < #cGraph do
    local s = ''
    if #cGraph - i ~= 1 and asciimeta[#cGraph - i] ~= nil then
      s = s .. string.rep(' ', 4) .. asciimeta[#cGraph - i].seq .. (asciimeta[#cGraph - i].save and ' s ' or '   ') .. time_ago(asciimeta[#cGraph - i].time)
    end
    if #cGraph - i == 1 then
      s = s .. string.rep(' ', 4) .. asciimeta[1].s
    end
    vim.api.nvim_buf_set_lines(bufnr, i, i + 1, false, { cGraph[#cGraph - i] .. s})
    i = i + 1
  end
  vim.api.nvim_buf_set_option(bufnr, 'modifiable', false)
end

_M.create_undo_buf = function(cGraph, asciimeta)
  local bufnr = vim.fn.bufnr(bufname)
  if bufnr == -1 then
    bufnr = vim.api.nvim_create_buf(false, true)
    vim.api.nvim_buf_set_name(bufnr, bufname)
  end
  local winid = vim.fn.bufwinid(bufnr)
  if winid == -1 then
    local screen_width = vim.api.nvim_get_option('columns')
    local cwin = 'silent keepalt topleft vertical ' .. tostring(math.floor(screen_width * 0.25)) .. ' new ' .. bufname
    vim.cmd(cwin)
    winid = vim.fn.bufwinid(bufnr)
  end

  -- window options: must be here --
  vim.api.nvim_win_set_option(winid, 'number', false)
  vim.api.nvim_win_set_option(winid, 'relativenumber', false)
  vim.api.nvim_win_set_option(winid, 'winfixwidth', true)
  vim.api.nvim_win_set_option(winid, 'wrap', false)
  vim.api.nvim_win_set_option(winid, 'spell', false)
  vim.api.nvim_win_set_option(winid, 'cursorline', true)
  vim.api.nvim_win_set_option(winid, 'signcolumn', 'no')
  -- buf options: must be here --
  vim.api.nvim_buf_set_option(bufnr, 'bufhidden', 'delete')
  vim.api.nvim_buf_set_option(bufnr, 'buftype', 'nowrite')
  vim.api.nvim_buf_set_option(bufnr, 'buflisted', false)
  vim.api.nvim_buf_set_option(bufnr, 'swapfile', false)
  vim.api.nvim_buf_set_option(bufnr, 'filetype', 'undotree')
  vim.api.nvim_buf_set_option(bufnr, 'modifiable', false)
  -- TODO: clear buf when rewrite buf content
  graph2buf(bufnr, cGraph, asciimeta)
  vim.api.nvim_buf_set_keymap(bufnr, 'n', 'j', '<cmd>lua require("undotree.utils").next_star(1)<cr>', { noremap = true, silent = true })
  vim.api.nvim_buf_set_keymap(bufnr, 'n', 'k', '<cmd>lua require("undotree.utils").next_star(-1)<cr>', { noremap = true, silent = true })
  vim.api.nvim_buf_set_keymap(bufnr, 'n', 'q', '<cmd>lua require("undotree.utils").delete_undo_buf()<cr>', { noremap = true, silent = true })

  -- TODO: FOCUS, make cursor to current postion
  if vim.fn.bufnr() ~= bufnr then
    vim.cmd(string.format('silent exe "%s"', "norm! " .. vim.fn.bufwinnr(bufnr) .. "\\<c-w>\\<c-w>"))
  end
  vim.fn.cursor({1, findstar(1)})
  -- print(asciimeta[#cGraph - 19 + 1].seq)  -- 19: line number
end

return _M
