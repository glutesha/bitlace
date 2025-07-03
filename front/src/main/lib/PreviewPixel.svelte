<script lang="ts">
  import { currentTheme } from '../theme';

  export let lit: boolean = false;

$: cn = lit ? `${$currentTheme.color} size-[15.4px] rounded-full shadow-lg ${$currentTheme.shadow}` : `bg-neutral-500 size-[15.4px] rounded-full`
</script>

<button class={cn} aria-label="pixel" 
  ></button>