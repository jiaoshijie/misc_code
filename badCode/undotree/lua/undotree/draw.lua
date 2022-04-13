local Draw = {}

-- node = [seq=`number`, ~time=`number`~, b=`table`]

-- no recursion
-- local draw = function(undo_info)
--   local sGraph = {}
--   local nseq = 0
--   local si = 1
--   local bs = 1  -- branch size
--   local cb = 1

--   local curinfo = undo_info.graph_info
--   while nseq ~= undo_info.seq_last do
--     if curinfo.seq == nseq then
--       if sGraph[si] == nil then sGraph[si] = '' end
--       for i = 0, bs, 1 do
--         if i == cb then
--           sGraph[si] = sGraph[si] .. tostring(nseq)
--         else
--           sGraph[si] = sGraph[si] .. 's'
--         end
--       end
--       curinfo = undo_info.graph_info
--       nseq = nseq + 1
--     end
--   end
-- end

-- recursion
local v_have = function(listp, item)
  for _, v in ipairs(listp) do
    if v == item then
      return true
    end
  end
  return false
end

local dfs
dfs = function(curnode, cb, sGraph, seq2index, done, d)
  if d.nseq == done then
    return 0
  end
  if curnode.seq == d.nseq then
    if sGraph[d.si] == nil then sGraph[d.si] = '' end
    sGraph[d.si] = sGraph[d.si] .. string.rep('s', cb - 1) .. tostring(d.nseq) .. string.rep('s', d.bs - cb)
    if seq2index[curnode.seq] == nil then
      seq2index[curnode.seq] = {}
    end
    seq2index[curnode.seq].time = curnode.time
    seq2index[curnode.seq].save = curnode.save
    d.nseq = d.nseq + 1
    d.si = d.si + 1
  end
  if curnode.b == nil or #curnode.b == 0 then
    return 0
  end
  if #curnode.b == 1 then
    return dfs(curnode.b[1], cb, sGraph, seq2index, done, d)
  end
  if #curnode.b > 1 then
    if sGraph[d.si] == nil then sGraph[d.si] = '' end
    if v_have(d.getp, curnode.seq) == false then
      table.insert(d.getp, curnode.seq)
      if sGraph[d.si] == '' then
        sGraph[d.si] = sGraph[d.si] .. string.rep('s', cb - 1) .. string.rep('p', #curnode.b) .. string.rep('s', d.bs - cb)
        d.si = d.si + 1
        d.bs = d.bs + #curnode.b - 1
      end
    end
    local t = 0
    for i, node in ipairs(curnode.b) do
      local bt = dfs(node, cb + i - 1 + t, sGraph, seq2index, done, d)
      t = t + bt
    end
    return #curnode.b - 1 + t
  end
  return 0
end

local replaceUsefulLeaveS2X = function(sGraph)
  for i = 1, #sGraph[#sGraph], 1 do
    local j = #sGraph
    if string.sub(sGraph[j], i, i) == 's' then
      while string.sub(sGraph[j], i, i) == 's' do
        sGraph[j] = string.sub(sGraph[j], 1, i - 1) .. 'x' .. string.sub(sGraph[j], i + 1, #sGraph[#sGraph])
        j = j - 1
      end
    end
  end
end

local darwCharGraph = function(charGraph, sGraph, asciimeta, seq2index)
  local i = 1
  local index = 0
  for _, s in ipairs(sGraph) do
    charGraph[i] = ''
    local j = 1
    while j <= #s do
      if string.sub(s, j, j) == 's' then
        charGraph[i] = charGraph[i] .. ' |'
        j = j + 1
      elseif string.sub(s, j, j) == 'p' then
        local ssum = 0
        for issnum = j, #s, 1 do
          if string.sub(s, issnum, issnum) == 's' then
            ssum = ssum + 1
          end
        end
        charGraph[i] = charGraph[i] .. ' |'
        j = j + 1
        charGraph[i] = charGraph[i] .. string.rep(' /', ssum + 1)
        j = j + 1
        while j <= #s and string.sub(s, j, j) == 'p' do
          i = i + 1
          charGraph[i] = string.rep(' |', j - 1) .. string.rep(' /', ssum + 1)
          j = j + 1
        end
        break
      elseif string.sub(s, j, j) == 'x' then
        if string.find(s, string.rep('x', #s - j + 1), j, true) then
          break
        end
        charGraph[i] = charGraph[i] .. '  '
        j = j + 1
      else
        -- make the tree more beautiful when only one branch
        if i~= 1 and string.sub(charGraph[i - 1], #charGraph[i] + 2, #charGraph[i] + 2) == '*' then
          charGraph[i + 1] = '' .. charGraph[i]
          charGraph[i] = charGraph[i] .. string.rep(' |', (#charGraph[i - 1] - #charGraph[i]) / 2)
          i = i + 1
        end
        while j <= #s and tonumber(string.sub(s, j, j)) do j = j + 1 end
        charGraph[i] = charGraph[i] .. ' *'
        if asciimeta[i] == nil then
          asciimeta[i] = {}
        end
        if index == 0 then
          asciimeta[i].s = "(Original)"
        else
          asciimeta[i].seq = index
          asciimeta[i].time = seq2index[index].time
          asciimeta[i].save = seq2index[index].save
        end
        index = index + 1
        -- charGraph[i] = charGraph[i] .. ' ' .. tonumber(string.sub(s, j, j))  -- NOTICE: looks so ugly
      end
    end
    i = i + 1
  end
end

local setmarks = function()
  -- TODO: set some symbols
  -- >num< : The current state',
  --   s   : Saved states',
  --   S   : The last saved state',
end

local draw = function(undo_info)
  local d = { nseq = 0, si = 1, bs = 1, getp = {} }
  local sGraph = {}
  local charGraph = {}
  local seq2index = {}
  local asciimeta = {}
  while d.nseq ~= undo_info.seq_last + 1 do
    -- dfs(curnode, cb, sGraph, bs, done, d)
    dfs(undo_info.graph_info, 1, sGraph, seq2index, undo_info.seq_last + 1, d)
  end
  replaceUsefulLeaveS2X(sGraph)
  darwCharGraph(charGraph, sGraph, asciimeta, seq2index)
  -- print(vim.inspect(asciimeta))
  return charGraph, asciimeta
end

-- draw(info)
return draw
