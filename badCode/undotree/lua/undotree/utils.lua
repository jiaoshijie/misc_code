local _M = {}
_M.findstar = function(lnum)
  local line = vim.fn.getline(lnum)
  local i = 1
  while i <= #line do
    if string.sub(line, i, i) == '*' then
      return i
    end
    i = i + 1
  end
  return nil
end


_M.next_star = function(direction)
  local lnum = vim.fn.line('.')
  while lnum > vim.fn.line('^') and lnum <= vim.fn.line('$') do
    lnum = lnum + direction
    local col = _M.findstar(lnum)
    if col then
      vim.fn.cursor({lnum, col})
      break
    end
  end
end

_M.delete_undo_buf = function()
  local bufnr = vim.fn.bufnr('jsj_undotree_1')
  if bufnr == -1 then return end
  if vim.fn.bufwinid(bufnr) then
    vim.api.nvim_win_close(vim.fn.bufwinid(bufnr), {force=true})
  end
  if bufnr ~= -1 then
    vim.api.nvim_buf_delete(bufnr, {force=true, unload=false})
  end
end

return _M
