local draw = require('undotree.draw')
local ui = require('undotree.ui')
local _M = {}
local ut = {}
local Node = {}

-- DONE

function Node:new(seq)
  local node = {}
  if seq then
    node.seq = seq
  else
    node.seq = -1
  end
  -- return setmetatable(node, self)
  return node
end

ut.tree = Node:new(0)

ut._parseEntries = function(input, output)
  if #input == 0 then return end
  if output.b == nil then output.b = {} end
  for _, e in ipairs(input) do
    local curnode = Node:new()
    curnode.seq = e.seq
    curnode.time = e.time
    curnode.save = e.save
    if e.alt ~= nil then
      ut._parseEntries(e.alt, output)
    end
    table.insert(output.b, curnode)
    output = curnode
    output.b = {}
  end
end

-- DONE

-- TODO
ut.update = function(flag)
  if flag then
    local undotree = vim.fn.undotree()
    -- local time = undotree.time_cur
    -- print(type(undotree.entries))
    -- print(vim.fn.strftime("%H:%M", time))
    -- for _, v in ipairs(undotree.entries) do
    --   if v.newhead ~= nil then
    --     ut.v = v
    --   end
    -- end
    print(vim.inspect(undotree))
  end
end

_M.setup = function()
  -- do something
end

ut._parseEntries(vim.fn.undotree().entries, ut.tree)
local info = { seq_last = vim.fn.undotree().seq_last, graph_info = ut.tree }
local chargraph, asciimeta = draw(info)
ui.create_undo_buf(chargraph, asciimeta)

return _M
