function [e a b] = mvprefl(patches, weights)
  sz = size(patches);
  dim = sz(1:2);
  numPatches = sz(3);

  [Haa Hab Hbb] = _mvprefl_findH(patches, weights);

  w = sum(sum(weights))(:) / dim(1) / dim(2);

  T = (Hbb * Hbb + w * w') \ Hbb;
  E = Haa + Hab * (T * Hbb * T - 2 * T) * Hab';

  [a e flag] = eigs(E, 1, "sm");
  if (flag != 0)
    e = NA;
    a = NA;
    b = NA;
    return;
  endif

  if (sum(a) < 0)
    a = -a;
  endif

  if (any(find(a <= 0)))
    e = NA;
    a = NA;
    b = NA;
    return;
  endif

  if (nargout > 2)
    b = -T * Hab' * a;
  endif
 
endfunction

%!test
%! _mvprefl_testhelpers
%! [patches weights a b] = genpatches();
%! [e a b] = mvprefl(patches, weights);
%! assert(e, 0, 1e-8);
%! e2 = objref(patches, weights, a, b);
%! assert(e, e2, 1e-8);

% vim:set syntax=octave:
