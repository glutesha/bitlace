<script lang="ts">
  import { currentTheme } from '../theme';

  export let lit: boolean = false;

$: cn = lit ? `${$currentTheme.color} size-3 rounded-full shadow-lg ${$currentTheme.shadow}` : `bg-neutral-400 size-3 rounded-full`
</script>

<button class={cn} aria-label="pixel" 
  ></button>